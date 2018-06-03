//
// Created by matyas on 05/02/2018.
//

#ifndef SEM_CSUGGESTOR_H
#define SEM_CSUGGESTOR_H

#include <string>
#include <vector>
#include <functional>
#include <map>
#include <set>
#include <algorithm>
#include <sstream>

template<typename T>
struct CIDExtractor
{
    std::vector<std::string> operator()(const T & item) const;
};

/**
 * Template class managing lookups and sorting them.
 * Parameter T is type of items stored and Extractor
 * is functor which extracts vector of strings from
 * item passed as parameter in operator(). The strings
 * are then separated into terms and used to save items T.
 * Class is defined in header file because it would not
 * compile separated.
 * @tparam T Items to be saved, removed and searched.
 * @tparam Extractor Helper function to extract identifier strings from items T.
 */
template <typename T, typename Extractor = CIDExtractor<T>>
class CSuggestor
{
public:
    /**
     * Name speaks for itself.
     * @param item Item to be inserted. No need for keys. Extractor takes care of that.
     * @return reference to self.
     */
    CSuggestor & Insert(const T & item)
    {
        for (const std::string & term: GetTerms(item))
            m_Suggestions.insert(make_pair(term, item));

        return *this;
    }

    /**
     * Name speaks for itself.
     * @param item Item to be removed.
     * @return reference to self.
     */
    CSuggestor & Remove(const T & item)
    {
        for (auto term: GetTerms(item))
        {
            auto bounds = m_Suggestions.equal_range(term);
            for (auto it = bounds.first; it != bounds.second; it++)
            {
                if (item == (*it).second)
                {
                    m_Suggestions.erase(it);
                    break;
                }
            }
        }

        return *this;
    }

    /**
     * Finds items and sorts them by significance.
     * The match is not always accurate as only one
     * term of only one identifier must match only one
     * term of query.
     * Example:\n
     * \n
     * Database:\n
     * 1 (ID = {"Hello WorlD", "wORlD"}),\n
     * 2 (ID = {"Hello world from Czech Republic"}),\n
     * 3 (ID = {"worlds"})\n
     * \n
     * Query "world" results in {1, 2} while order is not given.
     * Item 3 does not contain term "world" so it does not appear
     * in results.\n
     * Query "hello czech" returns {2, 1}. Item 2 must be first
     * as the match is better. However item 1 matches at least one
     * term and cannot be ignored.
     *
     * @param query string to be searched.
     * @return vector of items sorted by significance.
     */
    std::vector<T> Suggest(const std::string & query) const
    {
        std::set<std::string> queryTerms = Preprocess(query);
        std::map<T, int> frequencies;

        for (const std::string & term: queryTerms)
        {
            auto bounds = m_Suggestions.equal_range(term);

            for (auto it = bounds.first; it != bounds.second; it++)
            {
                auto p = *it;
                if (frequencies.find(p.second) == frequencies.end())
                    frequencies[p.second] = 1;
                else
                    frequencies[p.second]++;
            }
        }

        std::vector<std::pair<T, int>> pairs;

        for (const std::pair<T, int> & p: frequencies)
            pairs.push_back(p);

        auto cmp = [](const std::pair<T, int> & a, const std::pair<T, int> & b)
                    {
                        return a.second > b.second;
                    };

        std::sort(pairs.begin(), pairs.end(), cmp);

        std::vector<T> res;

        for (const std::pair<T, int> & p: pairs)
            res.push_back(p.first);

        return res;
    }

    void Clear()
    {
        m_Suggestions.clear();
    }

private:
    std::multimap<std::string, T> m_Suggestions;

    /**
     * Returns set of lowercase terms. terms are separated by whitespace.
     * @param s string to be parsed.
     * @return set of terms.
     */
    static std::set<std::string> Preprocess(const std::string &s)
    {
        std::set<std::string> result;
        std::stringstream ss(s);
        std::string item;

        while (ss >> item)
        {

            transform(item.begin(), item.end(), item.begin(), ::tolower);
            result.insert(item);
        }

        return result;
    }

    /**
     * Parses item into set of terms in its identifiers.
     * @param item item to be parsed.
     * @return set of lowercase terms that identify item.
     */
    static std::set<std::string> GetTerms(const T & item)
    {
        std::set<std::string> terms;
        Extractor getIDs = Extractor();

        for (const std::string & id: getIDs(item))
        {
            for (const std::string & term: Preprocess(id))
                terms.insert(term);
        }

        return terms;
    }
};



#endif //SEM_CSUGGESTOR_H
