#pragma once
#include <vector>
#include <variant>
#include <queue>

namespace itd::world
{
	class IObjectStorage
	{
	public:
		virtual ~IObjectStorage() = default;
		virtual void apply_pending_changes() = 0;
	};

	template <typename ObjectType>
	class ObjectStorageAPI : public IObjectStorage
	{
	protected:
		struct AddRequest { ObjectType object; };
		struct RemoveRequest { uint32_t unique_id; };
		using Request = std::variant<std::monostate, AddRequest, RemoveRequest>;

	public:
		virtual ~ObjectStorageAPI() = default;

	public:
		void push_back(const ObjectType& _object) { m_requests.push(AddRequest{ _object }); }
		void push_back(ObjectType&& _object) { m_requests.push(AddRequest{ std::move(_object) }); }
		void remove(uint32_t _unique_id) { m_requests.push(RemoveRequest{ _unique_id }); }
		const std::vector<ObjectType>& objects() const { return m_objects; }

	protected:
		std::vector<ObjectType> m_objects;
		std::queue<Request> m_requests;
	};

	template <typename ObjectType>
	class ObjectStorage : public ObjectStorageAPI<ObjectType>
	{
	private:
		using Base = ObjectStorageAPI<ObjectType>;
		using Base::m_objects;
		using Base::m_requests;
		using typename Base::AddRequest;
		using typename Base::RemoveRequest;

	public:
		virtual ~ObjectStorage() = default;

	public:
		void apply_pending_changes() override
		{
			while (!m_requests.empty())
			{
				if (auto* r = std::get_if<AddRequest>(&m_requests.front()))
				{
					m_objects.push_back(std::move(r->object));
				}
				else if (auto* r = std::get_if<RemoveRequest>(&m_requests.front()))
				{
					for (auto it = m_objects.begin(); it != m_objects.end();)
					{
						if (it->unique_id() == r->unique_id) it = m_objects.erase(it);
						else it++;
					}
				}
				m_requests.pop();
			}
		}
	};
}